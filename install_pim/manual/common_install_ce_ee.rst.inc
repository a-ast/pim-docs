Initializing Akeneo
-------------------

Configure the PIM via the ``.env`` file:

.. code-block:: yaml
    :linenos:

    APP_ENV=prod
    APP_DATABASE_HOST=localhost
    APP_DATABASE_PORT=null
    APP_DATABASE_NAME=akeneo_pim
    APP_DATABASE_USER=akeneo_pim
    APP_DATABASE_PASSWORD=akeneo_pim
    APP_INDEX_HOSTS='localhost:9200'


Launching the PIM in dev mode
-----------------------------

.. note::

   All `make` commands must be run from the PIM root directory, either created by the archive or from the composer create project above.

.. code-block:: bash

	$ NO_DOCKER=true make dev


Once this command is finished, the PIM is accessible at http://localhost:8080/

Launching the PIM in prod mode
------------------------------

.. code-block:: bash

   $ NO_DOCKER=true make prod

Once this command is finished, the PIM is accessible at http://localhost:8080/

Setup Akeneo
----------------------

Configuring Akeneo
******************

Akeneo PIM is configured with environment variables. The `Symfony documentation <https://symfony.com/doc/current/configuration.html#configuration-based-on-environment-variables>`_ explains how to use them.


Running jobs
************

Akeneo PIM implements a queue for the `jobs <../../import_and_export_data/index.html>`_, as a PHP daemon. This daemon is a Symfony command, that can only execute one job at a time. It does not consume any other job until the job is finished.

You can launch several daemons to allow the execution of several jobs in parallel. A daemon checks every 5 seconds the queue and executes the next job from the queue.

To launch a daemon, run the following command:

.. code-block:: bash

    $ php bin/console akeneo:batch:job-queue-consumer-daemon

If you want to execute only one job:

.. code-block:: bash

    $ php bin/console akeneo:batch:job-queue-consumer-daemon --run-once

.. warning::

   When stopping or destroying your containers, avoid frozen FPM containers by killing running job consumers. Restarting Docker is required otherwise.

   .. code-block:: bash

    $ php pkill -f job-queue-consumer-daemon